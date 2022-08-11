import os
from os.path import join
import email
 
class Corpus:
    def __init__(self, directory):
        self.dir = directory
     
    def emails(self):
        emails_list = os.listdir(self.dir) 
        for email in emails_list:
            if not "!" in email:
                filename = join(self.dir, email)
                with open(filename, 'r', encoding='utf-8') as f:    
                    yield email, f.read()
 
    @staticmethod
    def get_pred_dict(trigger_words, directory):
        """
        Compares email body with trigger words, 
        if body contains at least one trigger word,
        it is spam
        """
        pred_dict = {}
        curr_corpus = Corpus(directory)
        for fname, body in Corpus.emails(curr_corpus):
            message = email.message_from_string(body)
            if message.is_multipart():
                for part in message.walk():
                    if part.get_content_maintype() == "multipart":
                        continue
                    else:
                        new_body = part.get_payload().lower()
            else:
                new_body = message.get_payload().lower()
            if trigger_words:
                for key in trigger_words.keys():
                    if key in new_body.split():
                        pred_dict[fname] = "SPAM"
                        break
                    else:
                        pred_dict[fname] = "OK"
            else:
                pred_dict[fname] = "OK"
        return pred_dict
    