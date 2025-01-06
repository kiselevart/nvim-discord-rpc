local M = {}

-- Function to start the Discord RPC process in the background
function M.start_discord_rpc()
    -- Define the path to the discord-rpc binary
    local command = vim.fn.expand('~') .. '/projects/nvim-discord-rpc/bin/discord-rpc'

    -- Start the process in the background using jobstart
    vim.fn.jobstart(command, {
        on_exit = function(_, code)
            if code == 0 then
                print("Discord RPC started successfully")
            else
                print("Error starting Discord RPC")
            end
        end
    })
end

function get_current_file_info(info_type)
  if info_type == "full" then
    return vim.fn.expand('%:p')  -- Full path
  elseif info_type == "filename" then
    return vim.fn.expand('%:t')  -- Filename only
  elseif info_type == "directory" then
    return vim.fn.expand('%:p:h')  -- Directory only
  else
    return nil  -- Invalid type
  end
end

return M
