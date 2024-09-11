import dotenv


class EnvConfig:
  def __init__(self, env_path: str = ".env"):
    self._config = dotenv.dotenv_values(env_path)

  def getValue(self, key: str) -> str:
    return self._config[key]
