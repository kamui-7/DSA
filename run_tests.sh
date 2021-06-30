test_dir=build/bin

for tb in $test_dir/*; do
    eval $tb
    echo 
done;
