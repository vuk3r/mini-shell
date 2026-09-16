                 USER INPUT
                     │
                     ▼
             ┌──────────────┐
             │    Lexer     │
             │ tokenize     │
             └──────┬───────┘
                    │
                    ▼
             ┌──────────────┐
             │    Parser    │
             │ syntax/AST   │
             └──────┬───────┘
                    │
                    ▼
             ┌──────────────┐
             │  Expansion   │
             │ $VAR, *, ~   │
             └──────┬───────┘
                    │
                    ▼
             ┌──────────────┐
             │   Executor   │
             └──────┬───────┘
                    │
          ┌─────────┼──────────┐
          ▼         ▼          ▼
       builtin   external    pipeline
                  command
          │         │          │
          ▼         ▼          ▼
       chdir()   fork/exec   pipe/dup2