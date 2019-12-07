## nfa-construct
A C program on the command-line, which takes in a regular expression and produces an NFA that could then be formatted as a PNG file.
### This program uses graphviz and xdot.
 Installed via homebrew:
`brew install gcc graphiz xdot`
 
### Build the program
 Call `make` on the command-line to build.
 
### Declare a regular expression and convert to NFA
 Use the syntax `./toNFA 'EXPRESSION'` to generate a nfa.dot file within the directory.
 
 `ex: ./toNFA '(a+b)(c+d)*'`
 
 Convert this file into a picture using `dot -Tpng nfa1.dot -o nfa1.png`
 
 To generate more nfa's, simply use the syntax `./toNFA 'EXPRESSION'` to create another nfa.dot file, then convert to PNG using `dot -Tpng nfa.dot -o nfa2.png`, calling the second image `nfa2.png`.
 
 ### Supported Characters:
 `+ = union`
 `( ) = parenthesis`
 `* = kleene closure`
 `a-z = characters`

### updates
`12/6/19 - additional lambda moves`
