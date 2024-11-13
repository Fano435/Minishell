Resume de ce que j'ai compris du projet

- Un shell c'est un programme qui va interpreter et executer des commandes. 
En mode interactif, son entree est ce qui est tape au clavier.
En mode non-interactif, son entree est ce qui est lu d'un fichier.
- Bash est l'interpreteur de commande pour le systeme d'exploitation GNU.

Les etapes

1. Reads its input from a file or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules.
These tokens are separated by metacharacters. 
Alias expansion is performed by this step
3. Performs the various shell expansions
breaking the expanded tokens into lists of filenames and commands and arguments.
4. Performs any necessary redirections and removes the redirection operators and their operands from the argument list.
5. Executes the command
6. Optionally waits for the command to complete and collects its exit status
