Todas as listas de cartas no jogo foram implementadas utilizando listas duplamente encadeadas. Tanto os baralhos 
principais quanto as mãos criadas pelo computador utilizaram esse tipo de estrutura de dados.

A distribuição de cartas opera da seguinte maneira: um baralho principal é inicialmente definido com todas as 52 
cartas em ordem. Esse deck principal é então embaralhado, e, em seguida, 26 cartas são distribuídas aleatoriamente 
para dois decks secundários.

Um desses decks secundários é enviado para leitura pelo computador, que selecionará as melhores classificações 
possíveis. O código busca, de melhor para pior, cartas que se encaixem em uma determinada classificação entre todas 
as classificações possíveis. Se uma classificação for possível com base no deck secundário de 26 cartas, as cartas 
associadas a essa classificação são movidas para uma das mãos e removidas do deck secundário. O código verifica 
quais classificações são possíveis a cada iteração sobre uma das cinco mãos.

O processo é repetido para cada mão, resultando na seleção das melhores combinações de cartas para cada jogador. 
O objetivo é determinar a mão mais forte possível para cada jogador com base nas cartas disponíveis.