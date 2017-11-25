// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef EREWHON_CLIENT_SERVERCONNECTION_HPP
#define EREWHON_CLIENT_SERVERCONNECTION_HPP

#include <Nazara/Core/Signal.hpp>
#include <Nazara/Core/String.hpp>
#include <Client/ClientCommandStore.hpp>
#include <Shared/Protocol/Packets.hpp>

namespace ewn
{
	class ClientApplication;
	class ClientCommandStore;
	class NetworkReactor;

	class ServerConnection
	{
		friend ClientApplication;

		public:
			inline ServerConnection(ClientApplication& application);
			ServerConnection(const ServerConnection&) = delete;
			ServerConnection(ServerConnection&&) = delete;
			~ServerConnection() = default;

			bool Connect(const Nz::String& serverHostname, Nz::UInt32 data = 0);
			inline void Disconnect(Nz::UInt32 data = 0);

			inline bool IsConnected();

			template<typename T> void SendPacket(const T& packet);

			ServerConnection& operator=(const ServerConnection&) = delete;
			ServerConnection& operator=(ServerConnection&&) = delete;

			NazaraSignal(OnConnected,    ServerConnection* /*server*/, Nz::UInt32 /*data*/);
			NazaraSignal(OnDisconnected, ServerConnection* /*server*/, Nz::UInt32 /*data*/);

			// Packet reception signals
			NazaraSignal(OnArenaState,       ServerConnection* /*server*/, const Packets::ArenaState&       /*data*/);
			NazaraSignal(OnChatMessage,      ServerConnection* /*server*/, const Packets::ChatMessage&      /*data*/);
			NazaraSignal(OnControlSpaceship, ServerConnection* /*server*/, const Packets::ControlSpaceship& /*data*/);
			NazaraSignal(OnCreateSpaceship,  ServerConnection* /*server*/, const Packets::CreateSpaceship&  /*data*/);
			NazaraSignal(OnDeleteSpaceship,  ServerConnection* /*server*/, const Packets::DeleteSpaceship&  /*data*/);
			NazaraSignal(OnLoginFailure,     ServerConnection* /*server*/, const Packets::LoginFailure&     /*data*/);
			NazaraSignal(OnLoginSuccess,     ServerConnection* /*server*/, const Packets::LoginSuccess&     /*data*/);
			NazaraSignal(OnTimeSyncResponse, ServerConnection* /*server*/, const Packets::TimeSyncResponse& /*data*/);

		private:
			inline void DispatchIncomingPacket(Nz::NetPacket&& packet);
			inline void NotifyConnected(Nz::UInt32 data);
			inline void NotifyDisconnected(Nz::UInt32 data);

			ClientApplication& m_application;
			ClientCommandStore m_commandStore;
			NetworkReactor* m_networkReactor;
			std::size_t m_peerId;
			bool m_connected;
	};
}

#include <Client/ServerConnection.inl>

#endif // EREWHON_CLIENT_SERVERCONNECTION_HPP