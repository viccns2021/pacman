# PACMAN

Feito por 

Victor Cristiano do Nascimento Silva RA21080416

Daniel Espindola da Silva RA 11201720555

Ideia:

Fazer um jogo 3D de pacman com visão isométrica no qual o usuário conseguisse andar pelo mundo um mundo e interagir com blocos.
No jogo o player consegue movimentar o 


### Detecção de Colisão

Para o nosso projeto foi necessário implementar um algorítmo de detecção de colisão para que pudessemos fazer o player não atravessar as caixas. Embora seja possível implementar algorítmos complexos que lidam com o formato de cada objeto, optamos por implementar uma versão super simples que detecta a colisão entre 2 caixas. Portanto aproximamos o formato do player por uma caixa de tamanho similar que envolve ele. Isso permite que a checagem seja feita com comparações logicas apenas, sem nenhuma operação geométrica.
O Algoritmo é implementado pela função NOME que recebe a posição x,y,z da primeira box e seu tamanho, e a posição x,y,z da segunda box e seu tamanho.


Te
