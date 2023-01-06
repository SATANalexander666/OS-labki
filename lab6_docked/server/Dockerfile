FROM cmake-cppzmq

WORKDIR /app

ADD ./DockSrc /app/code

WORKDIR /app/build

RUN cmake ../code && \
    cmake --build . && \
    make
