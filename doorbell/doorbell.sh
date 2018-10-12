#!/bin/bash
bellButton=7
userId='user#81464074'
tgPath=/home/pi/tg
picPath=/home/pi/photo.jpg
cd ${tgPath}
gpio mode ${bellButton} in
while sleep 1; do
    echo '>>>>> Waiting for bell'
    if [ "$(gpio read ${bellButton})" -eq 0 ];
    then
	echo '>>>>> Calling bell pressed'
	echo '>>>>> Taking Photo'
	raspistill -w 1200 -h 900 -o ${picPath}
	echo '>>>>> Photo taken'
	echo '>>>>> Sending the Photo using Telegram'
	${tgPath}/bin/telegram-cli -RD -e "send_photo $userId $picPath"
        echo '>>>>> Photo sent'
    fi
done