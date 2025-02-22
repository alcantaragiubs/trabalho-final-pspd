Como criar imagem docker

`docker build -t pspd .`

Carregar imagem no kubernetes

`kind image load pspd`

Executar deploy 

`kubectl apply -f mpi-deployment.yaml`
`kubectl apply -f mpi-hostfile-configmap.yaml`

Como acessar terminal de um dos pods

`kubectl exec -it NAME-POD -- /bin/bash`

Como executar a aplicação
- necessário saber ip dos pods

`kubectl get pods -o wide`

- Teste de performaca. Soma do vetor distribuido 

O sistema realizou corretamente a soma de um vetor de 900000 posições, todas com valor 1, de forma distribuida nos 3 pods, incluindo o master.
Aplicação utiliza mpi_scatter.

`time mpirun -host pod1,pod2,pod3 -np 3 ./hello`

- Teste de falha

Executamos o falha.c e desligamos um pod. Isso resultou na falha completa da aplicação pois optamos em configurar o cluster em modo 'Deployment' e não 'Job'.

`mpirun -host pod1,pod2,pod3 -np 3 ./falha`