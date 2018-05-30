######################################################################
# Script automatico gerado por ‘trapezium', software de interpolação 
# e integracao numerica
######################################################################

# Nome da figura

nome <- 'Saida.R.png'
# Dados tabelados

x.tab <- c(1.600000, 2.500000, 3.000000, 4.200000, 5.400000, 6.700000);

y.tab <- c(-1.500000, -2.100000, 0.300000, 1.400000, 2.100000, 3.900000);

# Pontos interpolados, calculados pelo ‘trapezium'

x.int <- c(2.000000, 3.500000, 4.000000);

y.int <- c(-3.668846, 1.605210, 1.605194);

# Coeficientes do polinomio interpolador

coef <- c(136.775082, -213.546803, 121.197144, -31.988029, 3.989820, -0.189743);

# Numero de pontos da tabela

n.tab <- 6;

# Numero de pontos a interpolar

n.int <- 3;

# Numero de trapezios
n.tpz <- 20;
# Titulo
titulo <- "P(x) = ((-0.189743)*X^5 )+ ((3.989820)*X^4 )+ ((-31.988029)*X^3 )
+ ((121.197144)*X^2 )+ ((-213.546803)*X^1 )+ ((136.775082)*X^0 )";
#
	# Esta parte do script deve funcionar desde que os parametros
	# acima estejam devidamente preenchidos. E' a parte estatica
	# do script. Copiar exatamente desta forma no arquivo de saida.
	#
	# Calcula o valor interpolado para o pto x
	polinomio <- function(x, coef, n)
	{
			resultado <- 0;
			for(i in 1:n)
			{
					resultado <- resultado + coef[i]*(x^(i-1));
			}
			return(resultado);
	}
	#
	# Aqui comecam os comandos para plotar os resultados
	#
	# Cria o arquivo .png
	png(nome);
	# Gerando figura com 100 pontos
	gap <- (max(x.tab) - min(x.tab)) / 100;
	x <- seq(min(x.tab), max(x.tab), gap);
	y <- polinomio(x, coef, n.tab);
	plot(x,y,type='l', main=titulo);
	# Plota os trapezios
	h <- (max(x.tab) - min(x.tab)) / n.tpz;
	xp <- seq(min(x.tab), max(x.tab), h);
	yp <- polinomio(xp, coef, n.tab);
	for(i in 1:(n.tpz))
	{
	polygon(c(xp[i], xp[i], xp[i+1], xp[i+1], xp[i]),
	c(0, yp[i], yp[i+1], 0, 0),
	col='yellow', border='black', lty=2, lwd=1.3);
	
	}
	# Pontos da tabela
	for(i in 1:n.tab)
	{
			points(x.tab[i], y.tab[i], col='red', pch=19);
	}
	# Pontos interpolados
	
	for(i in 1:n.tab)
	{
			points(x.int[i], y.int[i], col='blue', pch=19);
	}
	# Encerra a criacao do arquivo .png
	dev.off();
	