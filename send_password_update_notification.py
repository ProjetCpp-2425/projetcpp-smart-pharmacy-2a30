import smtplib
import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from datetime import datetime

def send_email(to_email, full_name, cin, timestamp):
    from_email = "6ysfcrybaby9@gmail.com"  # Replace with your email
    password = "avzx yltx ihnn xgcs"  # Use an App Password if using Gmail with 2FA

    # Create a subject and a message
    subject = "Password Update Notification"
    message = f"Dear Admin,\n\nThe following user has updated their password:\n\n" \
              f"Full Name: {full_name}\nCIN: {cin}\nDate and Time: {timestamp}\n\n" \
              f"Please take note of this change.\n\nRegards,\nPharmease System"

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
    if len(sys.argv) != 4:
        print("Usage: python send_password_update_notification.py <admin_email> <full_name> <cin>")
        sys.exit(1)

    admin_email = sys.argv[1]
    full_name = sys.argv[2]
    cin = sys.argv[3]
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    send_email(admin_email, full_name, cin, timestamp)
