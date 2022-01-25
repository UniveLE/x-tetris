# Da eseguire con il comando "make" da terminale
# per compilare il progetto.

#variabili
exe=tetris
object=main.o ./src/game.o ./src/utils/utils.o ./src/utils/matrix/matrix.o ./src/utils/tetraminoes/tetraminoes.o ./src/utils/menu/menu.o ./src/utils/player/player.o ./src/utils/cpu/cpu.o
flags=-I./ -O3 -lrt -ansi -pedantic -Wno-unused-result
build_folder = /build_temp/

%.o: %.c		#creazione dei file con estensione -o
	@echo "Building $<"
	@gcc $(flags) -c $< -o $@

#creazione dell'eseguibile
$(exe): $(object)
	@gcc $(flags) $(object) -o $(exe)
	@echo "Project cleanup..."
	@rm -f -r *.o
	@find . -name "*.o" | xargs rm 
	@echo "Done, run with \"./$(exe)\""