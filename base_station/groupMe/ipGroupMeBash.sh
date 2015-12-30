# ipGroupMeBash
#  When run will send IP Address to the GroupMe as a Notice
#

echo " Raspberry Pi starting up.. Getting IP Address.."

IP_ADDR=$(ifconfig eth0 | sed -rn 's/^.*inet addr:(([0-9]+\.){3}[0-9]+).*$/\1/p')


curl -d '{"text" : "Your IP Address is $IP_ADDR", "bot_id" : "cc93be0be1f1df6e23832cc4e9"}' https://api.groupme.com/v3/bots/post
