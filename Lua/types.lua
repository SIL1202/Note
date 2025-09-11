-- Types

-- Nil:
local Nil = nil;
print(Nil);

if Nil then
  print("Nil is true");
else
  print("Nil is false");
end


-- Booleans:
-- Any Lua value is true, except for false and nil; in particular, the number 0 and the empty string "" are true
--
--@type any
local true_values = 0;
print(true_values);

true_values = "";
if true_values then
  print("empty str is true");
else
  print("empty str is false");
end
