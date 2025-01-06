local M = {}

function M.setup()
  local command = '../../bin/discord-rpc'
  os.execute(command)
end

return M
