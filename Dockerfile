
# Этап 1: сборка приложения
FROM ubuntu:24.04 AS builder

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY CMakeLists.txt ./
COPY include ./include
COPY src ./src
COPY tests ./tests

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --target matrix_calculator --parallel 2

# Этап 2: запуск приложения
FROM ubuntu:24.04 AS runtime

WORKDIR /app

COPY --from=builder /app/build/matrix_calculator ./matrix_calculator

CMD ["./matrix_calculator"]

