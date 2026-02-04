![License](https://img.shields.io/github/license/ThiagoBel/BigDragonOS)
![Status](https://img.shields.io/badge/status-experimental-orange)
![Release](https://img.shields.io/github/v/release/ThiagoBel/BigDragonOS)
![Downloads](https://img.shields.io/github/downloads/ThiagoBel/BigDragonOS/total)

# BigDragonOS
- Simulador de sistema operacional simples usando C++ (apenas Windows7+)

> Isso não é uma maquina virtual, é apenas um simulador, você ainda sim pode pegar vírus no seu computador usando esses comandos: **exec_apps**, **down_apps**, **open_apps**, **open_apps_libs**, etc

[Releases](https://github.com/ThiagoBel/BigDragonOS/releases)

# Como iniciar?
- Entre na pasta, vá até o aplicativo **bdOS.exe** e execute ele

# Informações
### Formatar
- Use o comando 'format_os' (Ele não deleta os aplicativo por segurança mesmo)
### Documentação
- Use o comando 'help' para ver todos os comandos do sistema
### Verificar versão
- Para verificar a sua versão do sistema, use o comando 'version'.
- Use o comando 'check_version' para verificar se sua versão é a versão mais atualizada do BigDragonOS
### Fotos
- Nova funcionalidade que chegou na 1.7, fotos coloridas
- Comandos: "down_photo (LINK)" , "open_photos" , "del_photo" , "rename_photo"
### Armazenamento
- Use o comando 'check_storage' para ver quantos MB o sistema utilizou
### Logs
- Use 'show_logs_error' para ver TODOS os erros que já apareceu para você.
- Use 'show_logs_history' para ver o histórico de comando.
- Use 'clear_logs' para limpar todas as logs.
## Configs
- Sistema de configurações do BigDragonOS (comando: 'Configs')
#### Mutex
- 'Mutex' é a opção de não poder abrir mais de um sistema, atualmente vem ativado por padrão, mas se quiser desativar, apenas usar o comando 'Configs', navegar até a opção e selecionar para desativar.
#### Sounds
- 'Sounds' são os sons do sistema (storage/configs/sounds/).
#### Logs
- 'Logs' são as coisas que acontecem no sistema (Todos os erros, historico de comandos, etc), usando o comando 'Configs' você pode ativar ou desativar as logs.
#### Clear cmd
- 'Clear cmd' é a opção de limpar o cmd depois de usar qualquer comando (use o comando 'Configs' para ativar ou desativar).
#### Discord Rich Presence (discord-rpc)
- Integração com Discord Rich Presence para exibição de status do bdOS.

## Security
#### Outdated_apps
- 'Outdated_apps' são comandos antigos que não são mais usados por segurança, para desativar o Outdated_apps, basta usar o comando 'Security', navegar até 'Outdated_apps', selecionar e escolher a opção de desativar, **NÃO RECOMENDO** fazer isso, pois essa função foi feita justamente para segurança.
#### Senhas
- Use o comando: 'Security', depois navegue até 'senhas', depois aperte em criar senha e crie sua senha (É muito fácil burlar o sistema de senha, cuidado).
#### AutoRun
- 'AutoRun' é uma nova funcionalidade que veio na versão 1.8, que serve basicamente para quando o usuário abrir o BigDragonOS, irá executar no terminal um determinado comando.
- Você pode editar o AutoRun usando 'edit_autorun'.
- Você pode desativar/ativar o AutoRun usando o comando 'Security'
## Tests
- O comando 'tests' serve para testar alguma coisa que possivelmente vai ser uma novidade no BigDragonOS
#### IMG1
- Imagem 1
#### IMG2
- Imagem 2 (melhor)
