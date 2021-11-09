import os
import json
import random
import requests
import textwrap

from owls import facts

someKey = os.environ.get('SOME_KEY')

# def getQuotes():
#     API_ENDPOINT = ''
#     response = requests.get(API_ENDPOINT, headers={'Authorization': 'TOKEN {}'.format(someKey)})

#     if response.ok:
#         quotes = json.loads(response.text).get('results')
#         return random.choice(quotes)

def lambda_handler(event, context):
    print(event)
    
    # text = textwrap.fill(text, 42, break_long_words=False)

    return {
        "statusCode": 200,
        "body": random.choice(facts)
    }