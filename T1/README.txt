- Todos os seguintes recursos foram implementados:
	- Efeitos:
		* Diminuir brilho; 
		* Negativo; 
	
	- Modificações:
		* Espelhamento; 
		* Rotaçaõ; 
		* Recorte; 
		* Redimensionamento; 
		* Seleção de sub-conjunto para ediçaõ; 


- A imagem a ser editada deve ser enviada como argumento pelo terminal, apenas ppm 
P3 são suportados. 

- A foto original pode ser re-editada quantas vezes for necessário, entretanto, os 
efeitos não são acumulativos. Todas as reedições serão aplicadas apenas no arquivo 
ppm original.  

- O código foi separado em arquivos diferentes para a main e para as especificações 
e implementações dos tipos abstratos de dados. 

- Para auxiliar na compilação o nome do arquivo ppm pode ser adicionado na seção 
"run:" do makefile. 
	* Ex: "$(BIN)/app teste.ppm" 

- Para utilizar o makefile é necessário possui as pastas obj, lib e bin no mesmo diretório. 

- O arquivo ppm é lido para uma struct, que recebe todos os pixeis e informações da
imagem. 

- Todas as alocações de memória referentes às imagens foram realizadas dinamicamente.   
