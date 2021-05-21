//--Find GCD function 
unsigned long int findGCD(unsigned long int a, unsigned long int b){
  unsigned long int c;
  while (1){
    c = a % b;
    if (c == 0) {return b; }
    a = b;
    b = c;
  }
  return 0;
}

unsigned long GCD = tasks[0]->period;
for (i = 1; i < numTasks, i++) {
  GCD = findGCD(GCD, tasks[i]->period);
}
