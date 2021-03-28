FROM gcc:10
COPY . .
RUN gcc -lm -o simpsonsecondrule main.c tinyexpr.c
CMD ["./simpsonsecondrule"]