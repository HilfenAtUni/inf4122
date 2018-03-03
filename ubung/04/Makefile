JAVA=java
JAVAC=javac
JFLAGS=-classpath . -encoding utf-8 -Xlint:all
DEBUG= -g

all: Sieve Eratosthenes

Eratosthenes:
	$(JAVAC) $(JFLAGS) $(DEBUG) Eratosthenes.java

Sieve:
	$(JAVAC) $(JFLAGS) $(DEBUG) Sieve.java

clean:
	rm -vfr *~ *.class

test:
	$(JAVA) Sieve
