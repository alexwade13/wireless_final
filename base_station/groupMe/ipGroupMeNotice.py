## Basestation - ipGroupMeNotice.py - for GymAware RaspPi
##
import subprocess
import datetime
today = datetime.date.today()
# Very Linux Specific - Get IP Address
arg='ip route list'
p=subprocess.Popen(arg,shell=True,stdout=subprocess.PIPE)
data = p.communicate()
split_data = data[0].split()
ipaddr = split_data[split_data.index('src')+1]
my_ip = 'Your ip is %s' %  ipaddr
msg = 'IP For RaspberryPi on %s' % today.strftime('%b %d %Y')
# Use GroupMe API to send the IP address
text = "\'{\"text\" : \"" + my_ip + msg + "\", \"bot_id\" : \"cc93be0be1f1df6e23832cc4e9\"}\'"
print(text)
subprocess.call(["curl", "-d", text, "https://api.groupme.com/v3/bots/post"])


