rm myProtoFile.pb.*

export PROTOBUF_PATH=/libs/grpc/bin/
export PROTO_FILES_PATH=vinoth/playground/protobuf

$PROTOBUF_PATH/protoc -I=$PROTO_FILES_PATH --cpp_out=./ myProtoFile.proto
