import pywhatkit as kit
import sys

# Receive phone number and message from Qt app
phone_number = sys.argv[1]
message = sys.argv[2]

# Send message through WhatsApp Web
try:
    kit.sendwhatmsg_instantly(f"+{phone_number}", message, wait_time=10, tab_close=True)
    print("Message sent successfully")
except Exception as e:
    print(f"Failed to send message: {str(e)}")
