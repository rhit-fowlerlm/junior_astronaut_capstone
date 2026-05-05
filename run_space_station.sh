if [ -z $XDG_SESSION_DESKTOP ]
then
echo "not in the desktop"
else
# source /home/space-station/env/bin/activate
python /home/space-station/main.py
fi
