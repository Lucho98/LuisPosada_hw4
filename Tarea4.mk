Resultados_hw4.pdf : Resultados_hw4.tex cuerdaextremosfijos.pdf cuerdapertubacion.pdf tambor.pdf sonido.wav cuerda_animation.mp4
	pdflatex Resultados_hw4.tex 

cuerdaextremosfijos.pdf cuerdapertubacion.pdf tambor.pdf sonido.wav cuerda_animation.mp4:plots.py
	python plots.py 
 
plots.py: Resultados_hw4.txt tambor.txt audio.txt animacion_hw4.txt 
	

Resultados_hw4.txt tambor.txt audio.txt animacion_hw4.txt: Ondas.x
	./Ondas.x 

Ondas.x : Ondas.c cond_ini_tambor.dat cond_ini_cuerda.dat
	gcc -Wall Ondas.c -o Ondas.x -lm -g


