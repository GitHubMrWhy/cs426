#!/bin/sh

openssl genrsa -out private 1024
openssl rsa -in private -pubout >public
openssl rand -out symme 20
