set C_TypeInfoList {{ 
"sparse_mm" : [[], { "return": [[], "void"]} , [{"ExternC" : 0}], [ {"a": [[], {"array": ["0", [4194304]]}] }, {"a_y": [[], {"scalar": "unsigned int"}] }, {"a_x": [[], {"scalar": "unsigned int"}] }, {"b": [[], {"array": [ {"scalar": "int"}, [2048]]}] }, {"b_y": [[], {"scalar": "int"}] }, {"b_x": [[], {"scalar": "int"}] }, {"c": [[], {"array": [ {"scalar": "int"}, [2048]]}] }],[],""], 
"0": [ "csr_t", {"typedef": [[[],"1"],""]}], 
"1": [ "csr", {"union": [[],[],[{ "csr_s": [[64], "2"]},{ "csr_v": [[],  {"scalar": "long long unsigned int"}]}],""]}], 
"2": [ "csr_s_t", {"typedef": [[[],"3"],""]}], 
"3": [ "csr_s_t", {"struct": [[],[],[{ "end_row": [[1],  {"scalar": "bool"}]},{ "column": [[31],  {"scalar": "unsigned int"}]},{ "value": [[],  {"scalar": "int"}]}],""]}]
}}
set moduleName sparse_mm
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set C_modelName {sparse_mm}
set C_modelType { void 0 }
set C_modelArgList { 
	{ a int 64 regular {array 4194304 { 1 3 } 3 1 }  }
	{ a_y int 32 regular  }
	{ a_x int 32 unused  }
	{ b int 32 regular {array 2048 { 1 3 } 1 1 }  }
	{ b_y int 32 unused  }
	{ b_x int 32 regular  }
	{ c int 32 regular {array 2048 { 0 3 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "a", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "a","cData": "void","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 4194303,"step" : 1}]}]}]} , 
 	{ "Name" : "a_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "a_y","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "a_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "a_x","cData": "unsigned int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "b", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "b","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 2047,"step" : 1}]}]}]} , 
 	{ "Name" : "b_y", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "b_y","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "b_x", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "b_x","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "c", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "c","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 2047,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 20
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ a_address0 sc_out sc_lv 22 signal 0 } 
	{ a_ce0 sc_out sc_logic 1 signal 0 } 
	{ a_q0 sc_in sc_lv 64 signal 0 } 
	{ a_y sc_in sc_lv 32 signal 1 } 
	{ a_x sc_in sc_lv 32 signal 2 } 
	{ b_address0 sc_out sc_lv 11 signal 3 } 
	{ b_ce0 sc_out sc_logic 1 signal 3 } 
	{ b_q0 sc_in sc_lv 32 signal 3 } 
	{ b_y sc_in sc_lv 32 signal 4 } 
	{ b_x sc_in sc_lv 32 signal 5 } 
	{ c_address0 sc_out sc_lv 11 signal 6 } 
	{ c_ce0 sc_out sc_logic 1 signal 6 } 
	{ c_we0 sc_out sc_logic 1 signal 6 } 
	{ c_d0 sc_out sc_lv 32 signal 6 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "a_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":22, "type": "signal", "bundle":{"name": "a", "role": "address0" }} , 
 	{ "name": "a_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "a", "role": "ce0" }} , 
 	{ "name": "a_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "a", "role": "q0" }} , 
 	{ "name": "a_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "a_y", "role": "default" }} , 
 	{ "name": "a_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "a_x", "role": "default" }} , 
 	{ "name": "b_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":11, "type": "signal", "bundle":{"name": "b", "role": "address0" }} , 
 	{ "name": "b_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "b", "role": "ce0" }} , 
 	{ "name": "b_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "b", "role": "q0" }} , 
 	{ "name": "b_y", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "b_y", "role": "default" }} , 
 	{ "name": "b_x", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "b_x", "role": "default" }} , 
 	{ "name": "c_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":11, "type": "signal", "bundle":{"name": "c", "role": "address0" }} , 
 	{ "name": "c_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "c", "role": "ce0" }} , 
 	{ "name": "c_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "c", "role": "we0" }} , 
 	{ "name": "c_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "c", "role": "d0" }}  ]}
set Spec2ImplPortList { 
	a { ap_memory {  { a_address0 mem_address 1 22 }  { a_ce0 mem_ce 1 1 }  { a_q0 mem_dout 0 64 } } }
	a_y { ap_none {  { a_y in_data 0 32 } } }
	a_x { ap_none {  { a_x in_data 0 32 } } }
	b { ap_memory {  { b_address0 mem_address 1 11 }  { b_ce0 mem_ce 1 1 }  { b_q0 mem_dout 0 32 } } }
	b_y { ap_none {  { b_y in_data 0 32 } } }
	b_x { ap_none {  { b_x in_data 0 32 } } }
	c { ap_memory {  { c_address0 mem_address 1 11 }  { c_ce0 mem_ce 1 1 }  { c_we0 mem_we 1 1 }  { c_d0 mem_din 1 32 } } }
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
	{ a 3 }
}
