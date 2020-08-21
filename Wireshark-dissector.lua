--https://www.wireshark.org/docs/wsdg_html_chunked/lua_module_Proto.html

--this filter heavily based on mika's blog:
--https://mika-s.github.io/wireshark/lua/dissector/usb/2019/07/23/creating-a-wireshark-usb-dissector-in-lua-1.html
--https://mika-s.github.io/wireshark/lua/dissector/2017/11/04/creating-a-wireshark-dissector-in-lua-1.html
--https://mika-s.github.io/wireshark/lua/dissector/2018/12/30/creating-port-independent-wireshark-dissectors-in-lua.html

custom_protocol = Proto("Custom",  "Custom Protocol") -- name of our protocol and its description.
--setting the fields types:
-- Header fields
message_length  = ProtoField.int32 ("custom.message_length"  , "messageLength"     , base.DEC) -- the first argument is how to refer it in the filters, the second is its name
--the last one is the way to represent it (here it is in decimal). 
opcode          = ProtoField.int32 ("custom.opcode"          , "opCode"            , base.DEC)

-- Payload fields
flags           = ProtoField.int32 ("custom.flags"           , "flags"             , base.DEC)
full_coll_name  = ProtoField.string("custom.full_coll_name"  , "fullCollectionName", base.ASCII)
query           = ProtoField.none  ("custom.query"           , "query"             , base.HEX)

response_flags  = ProtoField.int32 ("custom.response_flags"  , "responseFlags"     , base.DEC)
cursor_id       = ProtoField.int64 ("custom.cursor_id"       , "cursorId"          , base.DEC)
nothing       = ProtoField.none  ("custom.nothing"       , "nothing"         , base.HEX)
test       = ProtoField.int16  ("custom.test"       , "test"         , base.HEX)

--associating our protocol with the fields
custom_protocol.fields = {
  message_length, opcode,                     -- Header
  flags, full_coll_name, query,      -- MY_QUERY
  response_flags, cursor_id, nothing, test -- MY_REPLY
}

-- buffer is the packet, pinfo are the wireshark whole columns in the packet list and tree is a layer in the packet.
function custom_protocol.dissector(buffer, pinfo, tree)
    length = buffer:len()
    if length == 0 then return end

  --setting the protocol name in the column to out name (the first argument).
    pinfo.cols.protocol = custom_protocol.name

  -- adding a layer of custom Protocol Data to the packet
  
    local        subtree =    tree:add(custom_protocol, buffer(), "custom Protocol Data")
  
  --adding two sub trees in the layer of custom Protocol Data
  
    local  headerSubtree = subtree:add(custom_protocol, buffer(), "Header")
    local payloadSubtree = subtree:add(custom_protocol, buffer(), "Payload")

    -- Header- adding in little edian the field to the sub tree. the field is the obj buffer from 0 to the offset of 4 (it's int32). 
    headerSubtree:add_le(message_length, buffer(0,4))

    local opcode_number = buffer(4,4):le_uint() -- casting to int in little edian
    local opcode_name = get_opcode_name(opcode_number)
    headerSubtree:add_le(opcode,         buffer(4,4)):append_text(" (" .. opcode_name .. ")")

    -- Payload
    if opcode_name == " MY_QUERY" then
        local flags_number = buffer(8,4):le_uint()
        local flags_description = get_flag_description(flags_number)
        payloadSubtree:add_le(flags,      buffer(8,4)):append_text(" (" .. flags_description .. ")")

        -- Loop over string
        local string_length
        for i = 12, length - 1, 1 do
            if (buffer(i,1):le_uint() == 0) then
                string_length = i - 12
                break
            end
        end

        payloadSubtree:add_le(full_coll_name,   buffer(12,string_length))
        payloadSubtree:add_le(query,            buffer(12+string_length,length-string_length-12))
    elseif opcode_name == "MY_REPLY" then
        local response_flags_number = buffer(8,4):le_uint()
        local response_flags_description = get_response_flag_description(response_flags_number)

        payloadSubtree:add_le(response_flags,   buffer(8,4)):append_text(" (" .. response_flags_description .. ")")
        payloadSubtree:add_le(cursor_id,        buffer(12,8))
        payloadSubtree:add_le(test,        buffer(20,2))
        payloadSubtree:add_le(nothing,        buffer(22,length-22))
    end
end

function get_opcode_name(opcode)
    local opcode_name = "Unknown"

	    if opcode ==    1 then opcode_name = "MY_REPLY"
	elseif opcode == 2001 then opcode_name = "MY_UPDATE"
    elseif opcode == 2002 then opcode_name = "MY_INSERT"
    elseif opcode == 2003 then opcode_name = "RESERVED"
    elseif opcode == 2004 then opcode_name = "MY_QUERY"
    elseif opcode == 2005 then opcode_name = "MY_GET_MORE"
    elseif opcode == 2006 then opcode_name = "MY_DELETE"
    elseif opcode == 2007 then opcode_name = "MY_KILL_CURSORS"
    elseif opcode == 2010 then opcode_name = "MY_COMMAND"
    elseif opcode == 2011 then opcode_name = "MY_COMMANDREPLY" end

    return opcode_name
end

function get_flag_description(flags)
    local flags_description = "Unknown"

        if flags == 0 then flags_description = "Reserved"
    elseif flags == 1 then flags_description = "TailableCursor"
    elseif flags == 2 then flags_description = "SlaveOk.Allow"
    elseif flags == 3 then flags_description = "OplogReplay"
    elseif flags == 4 then flags_description = "NoCursorTimeout"
    elseif flags == 5 then flags_description = "AwaitData"
    elseif flags == 6 then flags_description = "Exhaust"
    elseif flags == 7 then flags_description = "Partial"
    elseif 8 <= flags and flags <= 31 then flags_description = "Reserved" end

    return flags_description
end

function get_response_flag_description(flags)
    local flags_description = "Unknown"

        if flags == 0 then flags_description = "CursorNotFound"
    elseif flags == 1 then flags_description = "QueryFailure"
    elseif flags == 2 then flags_description = "ShardConfigStale"
    elseif flags == 3 then flags_description = "AwaitCapable"
    elseif 4 <= flags and flags <= 31 then flags_description = "Reserved" end

    return flags_description
end

--associating the protocol with udp and port.

local tcp_port = DissectorTable.get("udp.port")
tcp_port:add(666, custom_protocol) 

