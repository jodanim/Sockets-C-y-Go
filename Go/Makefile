
GO          := go
mkfile_path := $(realpath $(MAKEFILE_LIST))
build_dir   := build
src_dir     := src
GOPATH      := $(dir $(mkfile_path))
export GOPATH


all: $(build_dir)/client $(build_dir)/server

$(build_dir)/client: $(wildcard $(src_dir)/client/*.go) $(src_dir)/main_client.go
	$(GO) build -o $@ ./$(src_dir)/main_client.go

$(build_dir)/server: $(wildcard $(src_dir)/server/*.go) $(src_dir)/main_server.go
	$(GO) build -o $@ ./$(src_dir)/main_server.go

.PHONY: clean all

clean:
	rm -rf $(build_dir)/*
