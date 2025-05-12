import imaplib, smtplib
from datetime import datetime


import email
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import decode_header


EMAIL = "eg89150319497@gmail.com"
RECIPIENT_EMAIL = "sawarinekodesu@gmail.com"
PASSWD = "wfnm ywuo fzeo brwf"

IMAP_SERVER = "imap.gmail.com"
IMAP_PORT = 993

SMTP_SERVER = "smtp.gmail.com"
SMTP_PORT = 587


def decode_header_value(header_value):
    decoded_parts = decode_header(header_value)
    result = ''
    for part, encoding in decoded_parts:
        if isinstance(part, bytes):
            result += part.decode(encoding or 'utf-8', errors='ignore')
        else:
            result += part
    return result


#####################
# SMTP SEND MESSAGE #
#####################

# msg = MIMEMultipart()
#
# msg["From"] = EMAIL
# msg["To"] = RECIPIENT_EMAIL
# msg["Subject"] = "Задание №6. Почтовый сервер"
# msg_body = f"Отправил - Егоров Александр Владиславович М3О-125БВ-24, Принял - Егоров Александр Владиславович М3О-125БВ-24. Время отправки - {datetime.now()}."
#
# msg.attach(MIMEText(msg_body, 'plain'))
#
# with smtplib.SMTP(SMTP_SERVER, SMTP_PORT) as server:
#     server.starttls() 
#     server.login(EMAIL, PASSWD)
#     server.send_message(msg)
#

#######################
# IMAP RECIVE MESSAGE #
######################

client = imaplib.IMAP4_SSL(IMAP_SERVER, IMAP_PORT)
client.login(EMAIL, PASSWD)

status_select, messages_count = client.select("INBOX")

if isinstance(messages_count[0], bytes): # Проверка на None
    print(f"Status: {status_select}\nMessages: {messages_count[0].decode()}") 
else:
    exit(1)

status_search, messages = client.search(None, 'ALL')

message_ids = messages[0].split()[-5:][::-1]

print('-' * 50)

for msg_id in message_ids:
    status, msg_data = client.fetch(msg_id, '(RFC822)')
    if status != 'OK':
        print(f'Не удалось получить письмо {msg_id.decode()}')
        continue

    raw_email = msg_data[0][1]
    message = email.message_from_bytes(raw_email)

    from_ = decode_header_value(message.get('From'))
    subject = decode_header_value(message.get('Subject'))
    date = message.get('Date')

    print(f"From: {from_}")
    print(f"Subject: {subject}")
    print(f"Date: {date}")
    print('-' * 50)

# Закрытие соединения
client.logout()

