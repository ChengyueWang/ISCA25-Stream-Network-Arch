source env.sh 
module load apptainer
chmod +wxr -R $CUR_RSN_WORKSPACE
export CUR_RSN_WORKSPACE_IN_CONTAINER=$(realpath --relative-to="$HOME" "$CUR_RSN_WORKSPACE")
APPTAINER_BINDPATH=  apptainer exec -e --fakeroot --writable $SANDBOX_LOC bash -c " cd ~ ;\
cd $CUR_RSN_WORKSPACE_IN_CONTAINER/BERT_HuggingFace ;\
rm -rf output ;\
rm -rf python_gold ;\
./run.sh 6 ; \
./run.sh 8 ; \
./clean.sh
"

# if use iterative mode 
# export CUR_RSN_WORKSPACE_IN_CONTAINER=$(realpath --relative-to="$HOME" "$CUR_RSN_WORKSPACE")
# APPTAINER_BINDPATH=  apptainer exec --env CUR_RSN_WORKSPACE_RELATIVE=$CUR_RSN_WORKSPACE_IN_CONTAINER -e --fakeroot --writable $SANDBOX_LOC bash 
# cd $CUR_RSN_WORKSPACE_RELATIVE/BERT_HuggingFace ;\
# rm -rf output ;\
# rm -rf python_gold ;\
# ./run.sh 6 ; \
# ./run.sh 8 ; \
# ./clean.sh
