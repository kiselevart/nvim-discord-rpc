local M = {}

function M.setup()
  local command = '../../bin/discord-rpc'
  print(command)

  local result = vim.fn.system(command)
  print(result)
end

return M
