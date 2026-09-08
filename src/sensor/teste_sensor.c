#include <stdio.h>
#include "sensor.h" 
// Funções pra eu testar:
// sensor_init
// sensor_normalize
// sensor_set_range
// sensor_normalize_buffer
// sensor_set_value
// sensor_get_value


// 
// FUNÇÕES DE TESTE (Fora do main)
// 
#include <stdio.h>
#include "sensor.h" 

// testa se o sensor inicia certinho
int teste_sensor_init() {
  Sensor s = sensor_init(0, 1024);
  // ve se o min é 0, max é 1024 e o buffer ta zerado
  if (s.min_value == 0 && s.max_value == 1024 && s.buffer[0] == 0) {
    return 1; // deu bom
  }
  return 0; // deu ruim
}

// testa a funcao map do sensor
int teste_sensor_normalize() {
  Sensor s = sensor_init(0, 256);
  int resultado = sensor_normalize(&s, 512);
  // jogando 512 na escala de 256 tem que dar 128
  if (resultado == 128) {
    return 1;
  }
  return 0;
}

// testa se troca o range direito
int teste_sensor_set_range() {
  Sensor s = sensor_init(0, 1024);
  sensor_set_range(&s, 10, 500);
  
  // confere se mudou pra 10 e 500
  if (s.min_value == 10 && s.max_value == 500) {
    return 1;
  }
  return 0;
}

// testa normalizar a lista toda de uma vez
int teste_sensor_normalize_buffer() {
  Sensor s = sensor_init(0, 100);
  int raw[2] = {0, 1023};
  int normalized[2];
  
  sensor_normalize_buffer(&s, raw, normalized);
  
  // o zero vira zero e o 1023 vira 100
  if (normalized[0] == 0 && normalized[1] == 100) {
    return 1;
  }
  return 0;
}

// testa colocar e pegar valor do buffer
int teste_sensor_set_and_get_value() {
  Sensor s = sensor_init(0, 1024);
  
  // bota 450 no indice 2 e ve se ta la
  sensor_set_value(&s, 2, 450);
  int valor = sensor_get_value(&s, 2);
  
  // se inventar um indice invalido tem que retornar -1
  int invalido = sensor_get_value(&s, 99);
  
  if (valor == 450 && invalido == -1) {
    return 1;
  }
  return 0;
}

int main() {
  int number_tests = 6;
  int count_passed_tests = 0;

  printf("starting tests\n");

  // roda o teste 1
  if (teste_sensor_init() == 1) {
      printf("Teste 1 (sensor_init): PASSOU\n");
      count_passed_tests++; 
  } else {
      printf("Teste 1 (sensor_init): FALHOU\n");
  }

  // roda o teste 2
  if (teste_sensor_normalize() == 1) {
      printf("Teste 2 (sensor_normalize): PASSOU\n");
      count_passed_tests++; 
  } else {
      printf("Teste 2 (sensor_normalize): FALHOU\n");
  }

  // roda o teste 3
  if (teste_sensor_set_range() == 1) {
      printf("Teste 3 (sensor_set_range): PASSOU\n");
      count_passed_tests++; 
  } else {
      printf("Teste 3 (sensor_set_range): FALHOU\n");
  }

  // roda o teste 4
  if (teste_sensor_normalize_buffer() == 1) {
      printf("Teste 4 (sensor_normalize_buffer): PASSOU\n");
      count_passed_tests++; 
  } else {
      printf("Teste 4 (sensor_normalize_buffer): FALHOU\n");
  }

  // roda os dois ultimos juntos
  if (teste_sensor_set_and_get_value() == 1) {
      printf("Testes 5 e 6 (set/get value): PASSOU\n");
      count_passed_tests += 2; 
  } else {
      printf("Testes 5 e 6 (set/get value): FALHOU\n");
  }

  // mostra o total no fim
  printf("\n--- Resultado Final ---\n");
  printf("Testes que passaram: %d de %d\n", count_passed_tests, number_tests);

  return 0;
}