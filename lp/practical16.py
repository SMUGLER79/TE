from sklearn.feature_extraction.text import TfidfVectorizer
import streamlit as st
from sklearn.metrics.pairwise import cosine_similarity
import json


with open('faqs.json', 'r') as f:
    faqs = json.load(f)

questions = [faq['question'] for faq in faqs]
answers = [faq['answer'] for faq in faqs]

vectiorize = TfidfVectorizer()
x = vectiorize.fit_transform(questions)

st.title("Chatbot")
st.write("Enter your Query: ")

userinput = st.text_input("You: ")

if userinput:
    inputVec = vectiorize.transform([userinput])
    simil = cosine_similarity(inputVec, x)
    ind = simil.argmax()

    if simil[0][ind] < 0.5:
        response = "🤖: I'm sorry, I didn't understand that. Can you rephrase?"
    else:
        response = f"🤖:  " + answers[ind]
    st.write(response)
