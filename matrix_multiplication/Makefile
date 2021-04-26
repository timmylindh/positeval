
all: compile generate multiply compare analyze

# Compare matrices
compare:
	bash comparator.sh ${RANGE} ${SIZE} ${NUM}

# Multiply matrices
multiply:
	bash multiplier.sh ${RANGE} ${SIZE} ${NUM}

# Generate matrices
generate:
	bash generator.sh ${RANGE} ${SIZE} ${NUM}

# Average Posit
analyze:
	bash analyzer.sh ${RANGE} ${SIZE} ${NUM}

# Compile the nessecary binaries
compile: bin/f32.out bin/f64.out bin/p32.out bin/gen.out bin/comp.out bin/analyzer.out

# Compile average
bin/analyzer.out:
	g++ -ffloat-store src/analyzer.cpp -o bin/analyzer.out

# Compile float32
bin/f32.out:
	g++ -ffloat-store src/float32.cpp -o bin/f32.out

# Compile float64
bin/f64.out:
	g++ -ffloat-store src/float64.cpp -o bin/f64.out

# Compile posit32
bin/p32.out: ../SoftPosit/build/Linux-x86_64-GCC/softposit.a
	g++ -ffloat-store -std=gnu++11 -o bin/p32.out src/posit32.cpp ../SoftPosit/build/Linux-x86_64-GCC/softposit.a -I../SoftPosit/build/Linux-x86_64-GCC  -O2

# Compile matrix generator
bin/gen.out:
	g++ -ffloat-store -o bin/gen.out src/generateMatrix.cpp

# Compile matrix comparator
bin/comp.out:
	g++ -ffloat-store -o bin/comp.out src/comparator.cpp

# Compile the SoftPosit library
../SoftPosit/build/Linux-x86_64-GCC/softposit.a:
	cd ../SoftPosit/build/Linux-x86_64-GCC; \
	make -j6 all

clean:
	rm -r matrices/in/*
	rm -r matrices/out/32/* matrices/out/64/* matrices/out/posit/*
	rm -r matrices/result/32/* matrices/result/posit/*