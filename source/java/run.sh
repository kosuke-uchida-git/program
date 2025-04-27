#if "tmp" directory exists, remove it
if [ -d "tmp" ]; then
  rm -r tmp
fi
#make "tmp" directory
mkdir tmp
#copy source files to "tmp" directory
cp \
classes/sort/SelectionSort.java \
classes/sort/BubbleSort.java \
classes/sort/QuickSort.java \
main/Main.java tmp
#move to "tmp" directory
cd tmp
#compile source files
javac *.java
#run the program
java Main
#move to the original directory
cd ..
#remove "tmp" directory
rm -r tmp