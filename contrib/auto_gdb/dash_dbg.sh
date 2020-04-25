#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.ubicoincore/ubicoind.pid file instead
ubicoin_pid=$(<~/.ubicoincore/testnet3/ubicoind.pid)
sudo gdb -batch -ex "source debug.gdb" ubicoind ${ubicoin_pid}
