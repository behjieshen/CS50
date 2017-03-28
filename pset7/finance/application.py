from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir
import time
import datetime

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == "POST":
        if "buy" in request.form:
            buy()
            flash("Bought!")
        else:
            sell()
            flash("Sold!")
    user_id = session['user_id']
    query = db.execute("SELECT * FROM portfolio WHERE id = :id ORDER BY symbol AND shares", id = user_id)
    result = query
    total_value = 0
    for i in range(len(result)):
        quotes = lookup(result[i]['symbol'])   
        result[i]['stock'] = quotes['name']
        result[i]['price'] = quotes['price']
        result[i]['total'] = round(result[i]['price'] * result[i]['shares'], 2)
        total_value += (result[i]['price'] * result[i]['shares'])
    dollar_symbol = "$"
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session['user_id'])
    total_value = round(total_value + cash[0]['cash'], 2)
    if not result:
        return render_template("index.html", items = [""], dollar = "", cash = cash, total_value = cash[0]['cash'])
    return render_template("index.html", items = result, dollar = dollar_symbol, cash = cash, total_value = total_value)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        symbol_input = request.form.get("symbol").upper()
        if len(symbol_input) < 1:
            return apology("missing symbol")
        quotes = lookup(symbol_input)
        shares_input = request.form.get("shares")
        try: 
            check_shares = int(shares_input)
        except ValueError:
            return apology("shares must be in numbers")
        else:
            if int(shares_input) < 0: 
                return apology("negative shares can't be bought")
            elif len(shares_input) < 1:
                return apology("missing shares")
            elif quotes == None:
                return apology("invalid symbol")
        user_id = session['user_id']
        
        query = db.execute("SELECT cash FROM users WHERE id = :id", id = user_id)
        cost = quotes['price'] * int(shares_input)
        cash = query[0]['cash']
        if cash < cost:
            return apology("not enough cash")
            
        unix = time.time()
        date = str(datetime.datetime.fromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S'))
        query = db.execute("SELECT * from portfolio WHERE id = :id AND symbol = :symbol", id = user_id, symbol = symbol_input)
        if not query:
            query = db.execute("INSERT INTO portfolio (id, symbol, shares) VALUES(:id, :symbol, :shares)", id = user_id, 
            symbol = symbol_input, shares = shares_input)
        else:
            query = db.execute("UPDATE portfolio SET shares = shares + :shares WHERE symbol = :symbol AND id = :id", 
            shares = shares_input, symbol = symbol_input, id = user_id)
        query = db.execute("INSERT INTO history (id, symbol, shares, price, total, time) VALUES(:id, :symbol, :shares, \
        :price, :total, :time)", id = user_id, symbol = symbol_input, shares = shares_input, price = quotes['price'],
        total = round(quotes['price'] * int(shares_input), 2), 
        time = str(datetime.datetime.fromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S')))
        cash_update = db.execute("UPDATE users SET cash = cash - :total_cost WHERE id = :id", total_cost = cost, id = user_id)
        return redirect(url_for("index"))
    else:
        return render_template("buy.html")

@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions."""
    query = db.execute("SELECT * FROM history WHERE id = :id ORDER BY time", id = session['user_id'])
    result = query
    dollar_symbol = "$"
    return render_template("history.html", items = result, dollar = dollar_symbol)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quotes = lookup(request.form.get("stock"))
        if quotes == None:
            return apology("invalid symbol")
        return render_template("price.html", name = quotes['name'], symbol = quotes['symbol'], price = quotes['price'])
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    #return apology("TODO")
    # if user reached route via POST (as by submitting a form via POST)
    session.clear()
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
            
        elif not request.form.get("confirm_password"):
            return apology("must provide confirm password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        password = request.form.get("password")
        confirm_password = request.form.get("confirm_password")

        # ensure username exists and password is correct
        if len(rows) == 1:
            return apology("username taken")
        elif password != confirm_password:
            return apology("passwords do not match")

        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username = request.form.get("username"), 
        hash=pwd_context.encrypt(password))
        if not result: 
            return apology("error")
        
        # remember which user has logged in
        session["user_id"] = ["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":
        
        symbol_input = request.form.get("symbol").upper()
        quotes = lookup(symbol_input)
        shares_input = request.form.get("shares")
        try: 
            check_shares = int(shares_input)
        except ValueError:
            return apology("shares must be in numbers")
        else:
            if len(symbol_input) < 1:
                return apology("missing symbol")
            elif int(shares_input) < 0: 
                return apology("negative shares can't be sold")
            elif len(shares_input) < 1:
                return apology("missing shares")
            elif quotes == None:
                return apology("invalid symbol")
        
        shares_input = check_shares
        user_id = session['user_id']
        unix = time.time()
        date = str(datetime.datetime.fromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S'))
        query = db.execute("SELECT * FROM portfolio WHERE id = :id AND symbol = :symbol", id = user_id, symbol = symbol_input)
        if not query:
            return apology("no stock exists for sale")
        if query[0]['shares'] < shares_input:
            return apology("you can't sell shares more than you have")
        
        stocks_value = quotes['price'] * shares_input
        remaining_shares = query[0]['shares'] - shares_input
        if remaining_shares <= 0:
            query = db.execute("DELETE FROM portfolio WHERE id = :id AND symbol = :symbol", id = user_id, symbol = symbol_input)
        else:
            query = db.execute("UPDATE portfolio SET shares = :shares WHERE id = :id AND symbol = :symbol", shares = remaining_shares,
        id = user_id, symbol = symbol_input)
        query = db.execute("UPDATE users SET cash = cash + :value WHERE id = :id", value = stocks_value, id = user_id)
        query = db.execute("INSERT INTO history (id, symbol, shares, price, total, time) VALUES(:id, :symbol, :shares, \
        :price, :total, :time)", id = user_id, symbol = symbol_input, shares = shares_input * -1, price = quotes['price'] * -1,
        total = round(quotes['price'] * int(shares_input), 2), 
        time = str(datetime.datetime.fromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S')))
        return redirect(url_for("index"))
    else:
        return render_template("sell.html")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "POST":
        user_id = session['user_id']
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirm_new_password = request.form.get("confirm_new_password")
        query = db.execute("SELECT * FROM users WHERE id = :id", id = user_id)
        if len(old_password) == 0 or len(new_password) == 0 or len(confirm_new_password) == 0:
            return apology("Please fill up all the fields")
        elif not pwd_context.verify(old_password, query[0]["hash"]):
            return apology("Old password is incorrect")
        elif old_password == new_password:
            return apology("Old password and new password are the same")
        elif new_password != confirm_new_password:
            return apology("New password and password confirmation are different")
        query = db.execute("UPDATE users SET hash = :hash WHERE id = :id", id = user_id, hash = pwd_context.encrypt(new_password))
        return redirect(url_for("login"))
    else:
        return render_template("password.html")

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        user_id = session['user_id']
        credit_card_number = request.form.get("credit_card_number")
        cash = request.form.get("cash")
        password = request.form.get("password")
        if len(credit_card_number) == 0 or len(cash) == 0 or len(password) == 0:
            return apology("Please fill up all the fiekds")
        try:  
            cash = float(cash)
            credit_card_number = int(credit_card_number)
        except ValueError:
            return apology("cash & credit_card_number must be in numbers")
        else:
            query = db.execute("SELECT * FROM users WHERE id = :id", id = user_id)
            if not pwd_context.verify(password, query[0]["hash"]):
                return apology("incorrect password")
        type_of_credit_card = credit(credit_card_number)
        if type_of_credit_card == "INVALID":
            return apology("credit card is invalid")
        query = db.execute("UPDATE users SET cash = cash + :cash WHERE id = :id", cash = cash, id = user_id)
        flash(type_of_credit_card + " " + str(credit_card_number) + " " + "was used to add" + " $" + str(cash))
        return redirect(url_for("index"))
    else:
        return render_template("cash.html")
    