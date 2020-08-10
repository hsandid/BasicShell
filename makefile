all: subtract sum ls generate basicShell
cleanFiles:
	rm subtract.class ls.class generate.class sum.class run *.txt
subtract:	
	javac subtract.java
sum:	
	javac sum.java
ls:	
	javac ls.java
generate:	
	javac generate.java
basic_shell:
	gcc -o run basicShell.c