TEMP=`date +%d%m`
mkdir masters-$TEMP
cp *.sh masters-$TEMP/
cp *.tex masters-$TEMP/
cp -r eps masters-$TEMP/
tar cfjv masters-$TEMP.tar.bz2 masters-$TEMP
rm -rf masters-$TEMP/

