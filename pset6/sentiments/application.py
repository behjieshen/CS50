# main application for sentiments

from flask import Flask, redirect, render_template, request, url_for

import helpers
import os
import sys
import nltk
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name, 100)
    
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")
    
    positive, negative, neutral = 0.0, 0.0, 0.0
    analyzer = Analyzer(positives, negatives)
    for i in range(len(tweets)):
        score = analyzer.analyze(tweets[i])
        if score > 0.0:
            positive += 1
        elif score < 0.0:
            negative += 1
        else:
            neutral += 1
    positive = positive / len(tweets) * 100
    negative = negative / len(tweets) * 100
    neutral = neutral / len(tweets) * 100

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
