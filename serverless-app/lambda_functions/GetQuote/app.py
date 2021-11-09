import os
import json
import time
import boto3
import random
import requests
import textwrap


someKey = os.environ.get('SOME_KEY')

def getQuotes():
    API_ENDPOINT = ''
    response = requests.get(API_ENDPOINT, headers={'Authorization': 'TOKEN {}'.format(paperQuotesToken)})

    if response.ok:
        quotes = json.loads(response.text).get('results')
        return random.choice(quotes)

def lambda_handler(event, context):
    print(event)
    quote = getQuotes()
    # text = quote['quote'] + ' by ' + quote['author']
    text = textwrap.fill(text, 42, break_long_words=False)

    return {
        "statusCode": 200,
        "body": json.dumps({
            "url": url,
            "text": text
        })
    }