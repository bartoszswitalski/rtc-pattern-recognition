#!/bin/bash

fileid="1mWYK8Nf2JPka0ZBnQZAqr2Jr45bgyAmG"
filename="model.pth"

curl -c ./cookie -s -L "https://drive.google.com/uc?export=download&id=${fileid}" > /dev/null
curl -Lb ./cookie "https://drive.google.com/uc?export=download&confirm=`awk '/download/ {print $NF}' ./cookie`&id=${fileid}" -o ${filename}
rm ./cookie
