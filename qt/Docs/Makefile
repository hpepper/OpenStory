all: storyteller.qhc

storyteller.qhc: Makefile storyteller.qhcp
	echo "Generating storyteller.qhc"
	${HOME}/Qt/5.9.8/gcc_64/bin/qcollectiongenerator storyteller.qhcp -o storyteller.qhc


storyteller.qch: Makefile storyteller.qhc storyteller.qhp *.html
	echo "Generating storyteller.qch"
	${HOME}/Qt/5.9.8/gcc_64/bin/qhelpgenerator storyteller.qhp -o storyteller.qch

clean:
	- rm storyteller.qhc
	- rm storyteller.qch
