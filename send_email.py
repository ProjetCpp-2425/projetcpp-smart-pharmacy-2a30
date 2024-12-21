import smtplib
import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

def send_email(to_email, message):
    from_email = "6ysfcrybaby9@gmail.com"  # Replace with your email
    password = "avzx yltx ihnn xgcs"  # Use an App Password if using Gmail with 2FA

    subject = "Password Reset Verification Code"

    msg = MIMEMultipart()
    msg['From'] = from_email
    msg['To'] = to_email
    msg['Subject'] = subject
    msg.attach(MIMEText(message, 'plain'))

    try:
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(from_email, password)
        server.send_message(msg)
        server.quit()
        print("Email sent successfully.")
        sys.exit(0)
    except Exception as e:
        print(f"Failed to send email: {e}")
        sys.exit(1)

if __name__ == "__main__":
    to_email = sys.argv[1]
    message = sys.argv[2]
    send_email(to_email, message)
