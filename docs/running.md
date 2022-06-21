# Running the Benchmark

## Execution Requirements

- HEBench Test Harness in Frontend v0.8.0-beta
- API Bridge v0.7.0-beta
- Provided config file `benchmark_config.yaml`

## Running the Benchmark

```bash
export SUBMISSION_REPO_DIR="/path/to/repo/dir"
export BACKEND_INSTALL_DIR=$SUBMISSION_REPO_DIR/install
cd $TEST_HARNESS_INSTALL_DIR
mkdir $HOME/submission_0024_report
./test_harness --backend $BACKEND_INSTALL_DIR/libsubmission_0024.so --config_file $SUBMISSION_REPO_DIR/benchmark_config.yaml --report_root_path $HOME/submission_0024_report --single_path_report
```

This will run Test Harness to benchmark the backend submission. The reports of the run will be stored in `$HOME/submission_0024_report` . Check the officially submitted reports for comparison.

