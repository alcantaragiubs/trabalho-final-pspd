# Universidade de Brasília
## Programação para Sistemas Paralelos e Distribuídos
### Projeto Final - Kubernetes

#### Alunos
- Breno Henrique de Souza - 202015984
- Giulia Domingues de Alcantara - 180121308
- Samuel Alves Sato - 200069322
- Valderson Pontes da Silva Junior - 190020521

#### Introdução
Este relatório tem como objetivo documentar.

#### Metodologia
Para a realização da atividade proposta

#### Cluster Kubernetes
##### O que é 
Kubernetes é uma plataforma de código aberto, portátil e extensível para gerenciar cargas de trabalho e serviços conteinerizados. Ele facilita a configuração declarativa e a automação, permitindo que aplicações sejam executadas de forma eficiente e escalável. Com um ecossistema em rápido crescimento, Kubernetes oferece suporte a diversas ferramentas e serviços que auxiliam na administração e no funcionamento do cluster. [1]

Um cluster Kubernetes é formado por um conjunto de máquinas que trabalham juntas para executar aplicações em contêineres. Ele é composto por um plano de controle, responsável por gerenciar o cluster, manter o estado desejado e agendar workloads, e pelos nós workers, que são responsáveis por executar os contêineres e as aplicações. Dentro dos nós, os pods representam a menor unidade implantável e podem conter um ou mais contêineres, garantindo flexibilidade na execução das cargas de trabalho. [1]

Além da estrutura básica, Kubernetes possui mecanismos para gerenciar a comunicação entre as aplicações por meio de serviços, balanceamento de carga e recursos de rede. Também oferece opções para armazenamento, permitindo que os dados sejam mantidos de forma persistente ou temporária conforme a necessidade das aplicações. Para garantir a segurança, Kubernetes disponibiliza diversas configurações e políticas que ajudam a proteger os workloads e a definir boas práticas de administração do cluster. [1]

Em resumo, Kubernetes é uma solução poderosa para automatizar a implantação, escala e operação de aplicativos baseados em contêineres. Ele simplifica a gestão da infraestrutura, garantindo eficiência, flexibilidade e alta disponibilidade para aplicações modernas. [1]

##### Passo a Passo de Montagem 
1. Criação do script de instalação básica do Kubernetes `common.sh`:
  - O script contém todos os comandos utilizados pelo grupo para a instalação das configurações;
  - Ele está disponível na pasta do projeto;
  - Esse arquivo deve ser executado nas três máquinas: master, worker01 e worker 02, com o comando:
```bash
sudo ./common.sh
```
2. Criação do script de configuração da master `master.sh`:
  - O script contém todos os comandos utilizados pelo grupo para a configuração da máquina master;
  - Ele está disponível na pasta do projeto;
  - Esse arquivo deve ser executado apenas na master, com o seguinte comando:
```bash
bash ./master.sh
```
3. Criação do Dashboard de Monitoramento:
- Instalação do `helm`:
```bash
curl https://get.helm.sh/helm-v3.12.0-linux-amd64.tar.gz -o helm-v3.12.0-linux-amd64.tar.gz
```
- Adição do repositório kubernetes-dashboard
```bash
helm repo add kubernetes-dashboard https://kubernetes.github.io/dashboard/
```
- Deploy de uma Release do Helm chamada 'kubernetes-dashboard' utilizando o chart do kubernetes-dashboard:
```bash
helm upgrade --install kubernetes-dashboard kubernetes-dashboard/kubernetes-dashboard --create-namespace --namespace kubernetes-dashboard
```
- Habilitar o acesso ao Dashboard:
```bash
kubectl -n kubernetes-dashboard port-forward svc/kubernetes-dashboard-kong-proxy 8443:443
```
- Acesse o link disponibilizado do dashboard via: [https://localhost:8443/](https://localhost:8443/)
- Criação do Usuário Admin `dashboard-adminuser.yaml`:
  - Criar o arquivo:
  ```bash
  nano dashboard-adminuser.yaml
  ```
  - Adicionar o conteúdo:
    ```bash
    apiVersion: v1
    kind: ServiceAccount
    metadata:
      name: admin-user
      namespace: kubernetes-dashboard
    apiVersion: rbac.authorization.k8s.io/v1
    kind: ClusterRoleBinding
    metadata:
      name: admin-user
    roleRef:
      apiGroup: rbac.authorization.k8s.io
      kind: ClusterRole
      name: cluster-admin
    subjects:
    - kind: ServiceAccount
      name: admin-user
      namespace: kubernetes-dashboard
    ```
  - Aplique as mudanças:
    ```bash
    kubectl apply -f dashboard-adminuser.yaml
    ```
- Gere o Token de Autenticação:
  ```bash
  kubectl -n kubernetes-dashboard create token admin-user
  ```
    * Obs: O dashbaord foi criado utilizando-se a documentação oficial do Kubernetes [2].

##### Testes e Resultados
###### 1. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 2. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### Spark com Kubernetes
##### Como funciona
A integração do Spark com o Kubernetes...
##### Passo a Passo de Montagem 

##### Testes e Resultados
###### 1. Teste de Carga
O teste foi feito

Resultados Apresentdos:

###### 2. Teste de Performance
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 5. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 6. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### MPI/OpenMP com Kubernetes
##### Como funciona
A integração do Spark com o Kubernetes...
##### Passo a Passo de Montagem 

##### Testes e Resultados
###### 1. Teste de Carga
O teste foi feito

Resultados Apresentdos:

###### 2. Teste de Performance
O teste foi feito

Resultados Apresentados:

###### 3. Teste de Alta Disponibilidade
O teste foi feito

Resultados Apresentados:

###### 4. Teste de Escalabilidade
O teste foi feito

Resultados Apresentados:

###### 5. Teste de Orquestração
O teste foi feito

Resultados Apresentados:

###### 6. Teste de Escalonamento
O teste foi feito

Resultados Apresentados:

#### Cloud Native
##### O que é 
Cloud Native é 
##### Tópico 2
##### Tópico 3
##### Tópico 4

#### Conclusão 
##### Sobre o Experimento

##### Percepção dos Estudantes

##### Autoavaliação 

##### Referências
[1] KUBERNETES. Conceitos. Disponível em: [https://kubernetes.io/docs/concepts/](https://kubernetes.io/docs/concepts/). Acesso em: 20 fev. 2025.

[2] KUBERNETES. Dashboard. Disponível em: [https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/](https://kubernetes.io/docs/tasks/access-application-cluster/web-ui-dashboard/). Acesso em: 20 fev. 2025. 
