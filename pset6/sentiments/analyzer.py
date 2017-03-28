# analyzes twitter comments

import nltk

positive_words = []
negative_words = []


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = positives
        self.negatives = negatives

        with open(positives) as f:
            for line in f:
                if line.startswith(';') == False:
                    positive_words.append(line.strip(" "))
        
        with open(negatives) as f:
            for line in f: 
                if line.startswith(';') == False:
                    negative_words.append(line.strip(" "))

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        counter = 0
        for i in range(len(tokens)):
            for j in range(len(positive_words)):
                if tokens[i].lower() == positive_words[j].lower().strip("\n"):
                    counter += 1
            for k in range(len(negative_words)):
                if tokens[i].lower() == negative_words[k].lower().strip("\n"):
                    counter -= 1
        return counter
