./server
./client

1. Basic Commands
#client1
> login alex

#client2
> login denis

#anyclient
> whoisonline
> whoami

2. MESSAGING
#denis client
> message alex Hey alex, how are you?

#reply
# alex client
> reply 1 denis I'm doing great, thanks!

# denis receives:
[Reply to 1][DENIS]: I'm doing great, thanks!

3. Offline messages
# alex logs out
> logout

# DENIS sends message to offline ALEX
> message alex Are you there?

# When ALEX logs back in
> login alex

4. CHAT HISTORY
# DENIS checks chat history with ALEX
> gethistory alex

5. ERROR CASES
# Trying to login twice
> login alex
# Messaging without login
> message denis Hello
# Invalid command
> test
# Messaging yourself
> gethistory denis
