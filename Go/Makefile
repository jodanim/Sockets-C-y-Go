
GO          := go
mkfile_path := $(realpath $(MAKEFILE_LIST))
build_dir   := build
src_dir     := src
GOPATH      := $(dir $(mkfile_path))
export GOPATH


all: $(build_dir)/client $(build_dir)/server

$(build_dir)/client: $(wildcard $(srd_dir)/client/*.go)
	$(GO) build -o $@ ./$(src_dir)/main_client.go

$(build_dir)/server: $(wildcard $(srd_dir)/server/*.go)
	$(GO) build -o $@ ./$(src_dir)/main_server.go

.PHONY: clean

clean:
	rm -rf $(build_dir)/*
