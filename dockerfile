FROM gcc:latest
COPY . /usr/src
WORKDIR /usr/src
RUN make
CMD [ "./tetris" ]
