#!/bin/sh

function help() {
    echo "usage: $0 [c | py | all] ..."
    echo "c [filter]  - only run cmocka tests, optionally filter test"
    echo "py ...      - only run pytest tests, args are passed on"
    echo "all         - run all tests"
    exit 1
}

# cmocka runner
function _cmocka() {
    filter=""
    if [[ -n $1 ]]; then
        filter="-iname *$1*"
    fi

    for test_file in $(find ./build/bin -executable -type f $filter); do
        echo "---------------------------------"
        $test_file
    done
}

# pytest runner
function _pytest() {
    PYTHONPATH=dsa pytest test/ $@
}

if [[ -z $1 ]]; then
    help
fi

if [[ $1 == "all" ]]; then 
    shift
    _cmocka
    echo
    _pytest
elif [[ $1 == "py" ]]; then
    shift
    _pytest $@
elif [[ $1 == "c" ]]; then
    shift
    _cmocka $@
fi
