# PACMAN

Feito por 

Victor Cristiano do Nascimento Silva RA21080416

Daniel Espindola da Silva RA 11201720555

### Ideia:

Fazer um jogo 3D de pacman com visão isométrica no qual o usuário conseguisse andar pelo mundo um mundo e interagir com blocos.

No jogo o player consegue movimentar o Pacman no plano e fazer o movimmento de pulo.

### Textura

Fizemos uma camada de textura no chão para simular a grama. a ideia era tbm colocar uma textura no pacman, mas conseguimos apenas mudar a sua cor.

Para isso usamos um png de grama e separamos um shader para  especificar apenas a textura. E a função model para mexer nos shaders de textura 

### Movimentação

Colocamos para interagir com o personagem as teclas A,W,S,D e SPACE sendo SPACE o pulo feito por um a equação que deixa o pulo mais fluido.

position_y = jumpHeight * (jumpSpeed * jumpTime - 0.5f * gravity * jumpTime * jumpTime);

A fórmula é derivada da equação de movimento vertical em um campo gravitacional constante


### Detecção de Colisão

Para o nosso projeto foi necessário implementar um algorítmo de detecção de colisão para que pudessemos fazer o player não atravessar as caixas. Embora seja possível implementar algorítmos complexos que lidam com o formato de cada objeto, optamos por implementar uma versão super simples que detecta a colisão entre 2 caixas. Portanto aproximamos o formato do player por uma caixa de tamanho similar que envolve ele. Isso permite que a checagem seja feita com comparações logicas apenas, sem nenhuma operação geométrica.
O Algoritmo é implementado pela função isColliding que recebe a posição x,y,z da primeira box e seu tamanho, e a posição x,y,z da segunda box e seu tamanho.

Para o player interagir foram colocados 3 blocos em tamanhos e distâncias diferentes, por conta da colisão é possível pular em cimas dos blocos e cair depois. 


